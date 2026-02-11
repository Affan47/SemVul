loadModel(const char* filename, FMatrix3x3& matrix)
{
    const char* ext = strrchr(filename, '.');
    if (ext && strcasecmp(ext, ".stl") == 0)
    {
        return loadModelSTL(filename, matrix);
    }
    if (filename[0] == '#' && binaryMeshBlob != NULL)
    {
        SimpleModel* m = new SimpleModel();

        while(*filename == '#')
        {
            filename++;

            m->volumes.push_back(SimpleVolume());
            SimpleVolume* vol = &m->volumes[m->volumes.size()-1];
            int32_t n, pNr = 0;
            if (fread(&n, 1, sizeof(int32_t), binaryMeshBlob) < 1)
                return NULL;
            printf("Reading mesh from binary blob with %i vertexes\n", n);
            Point3 v[3];
            while(n)
            {
                float f[3];
                if (fread(f, 3, sizeof(float), binaryMeshBlob) < 1)
                    return NULL;
                FPoint3 fp(f[0], f[1], f[2]);
                v[pNr++] = matrix.apply(fp);
                if (pNr == 3)
                {
                    vol->addFace(v[0], v[1], v[2]);
                    pNr = 0;
                }
                n--;
            }
        }
        return m;
    }
    return NULL;
}
