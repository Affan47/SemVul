calctangents(bool areaweight = true)
{
    Vec3 *tangent = new Vec3[2*vmap.length()], *bitangent = tangent+vmap.length();
    memset(tangent, 0, 2*vmap.length()*sizeof(Vec3));
    loopv(triangles)
    {
        const triangle &t = triangles[i];
        sharedvert &i0 = vmap[t.vert[0]],
                   &i1 = vmap[t.vert[1]],
                   &i2 = vmap[t.vert[2]];

        Vec3 v0(epositions[i0.index]), e1 = Vec3(epositions[i1.index]) - v0, e2 = Vec3(epositions[i2.index]) - v0;

        double u1 = etexcoords[i1.index].x - etexcoords[i0.index].x, v1 = etexcoords[i1.index].y - etexcoords[i0.index].y,
               u2 = etexcoords[i2.index].x - etexcoords[i0.index].x, v2 = etexcoords[i2.index].y - etexcoords[i0.index].y;
        Vec3 u = e2*v1 - e1*v2,
             v = e2*u1 - e1*u2;

        if(e2.cross(e1).dot(v.cross(u)) < 0)
        {
            u = -u;
            v = -v;
        }

        if(!areaweight)
        {
            u = u.normalize();
            v = v.normalize();
        }

        loopj(3)
        {
            tangent[t.vert[j]] += u;
            bitangent[t.vert[j]] += v;
        }
    }
    loopv(vmap)
    {
        const Vec3 &n = enormals[vmap[i].weld],
                   &t = tangent[i],
                   &bt = bitangent[i];
        etangents.add(Vec4((t - n*n.dot(t)).normalize(), n.cross(t).dot(bt) < 0 ? -1 : 1));
    }
    delete[] tangent;
}
