loadsmd(const char *filename, const filespec &spec)
{
    stream *f = openfile(filename, "r");
    if(!f) return false;

    resetimporter();

    char buf[512];
    int version = -1, firstframe = eframes.length();
    bool hastriangles = false;
    while(f->getline(buf, sizeof(buf)))
    {
        char *curbuf = buf;
        if(smd::skipcomment(curbuf)) continue;
        if(sscanf(curbuf, " version %d", &version) == 1)
        {
            if(version != 1) { delete f; return false; }
        }
        else if(!strncmp(curbuf, "nodes", 5))
            smd::readnodes(f, buf, sizeof(buf));
        else if(!strncmp(curbuf, "triangles", 9))
        {
            smd::readtriangles(f, buf, sizeof(buf));
            hastriangles = true;
        }
        else if(!strncmp(curbuf, "skeleton", 8))
            smd::readframes(f, buf, sizeof(buf));
        else if(!strncmp(curbuf, "vertexanimation", 15))
            smd::skipsection(f, buf, sizeof(buf));
    }

    delete f;

    if(poses.length() && ejoints.length() && poses.length() != ejoints.length()) return false;

    if(hastriangles)
    {
        eframes.setsize(firstframe);
        smoothverts();
        makemeshes();
        makeanims();
    }
    else
    {
        eanim &a = eanims.add();
        if(spec.name) a.name = getnamekey(spec.name);
        else
        {
            string name;
            copystring(name, filename);
            char *end = strrchr(name, '.');
            if(end) *end = '\0';
            a.name = getnamekey(name);
        }
        a.startframe = firstframe;
        a.fps = spec.fps;
        a.flags = spec.flags;
        if(spec.endframe >= 0) a.endframe = a.startframe + spec.endframe;
        else if(spec.endframe < -1) a.endframe = a.startframe + max(eframes.length() - a.startframe + spec.endframe + 1, 0);
        a.startframe += spec.startframe;
        makeanims();
    }

    return true;
}
