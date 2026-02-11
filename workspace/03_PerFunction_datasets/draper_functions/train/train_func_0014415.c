setPosDeltas(const hsTArray<hsVector3>& verts) {
    delete[] fPosDelta;
    fNumVerts = verts.getSize();
    fPosDelta = new unsigned char[fNumVerts * CalcPosStride(fEncoding)];

    switch (fEncoding.getCode() & plSpanEncoding::kPosMask) {
    case plSpanEncoding::kPos888:
        {
            unsigned char* pp = fPosDelta;
            for (unsigned int i=0; i<fNumVerts; i++) {
                pp[0] = (unsigned char)(verts[i].X / fEncoding.getPosScale());
                pp[1] = (unsigned char)(verts[i].Y / fEncoding.getPosScale());
                pp[2] = (unsigned char)(verts[i].Z / fEncoding.getPosScale());
                pp += 3;
            }
        }
        break;
    case plSpanEncoding::kPos161616:
        {
            unsigned short* pp = (unsigned short*)fPosDelta;
            for (unsigned int i=0; i<fNumVerts; i++) {
                pp[0] = (unsigned short)(verts[i].X / fEncoding.getPosScale());
                pp[1] = (unsigned short)(verts[i].X / fEncoding.getPosScale());
                pp[2] = (unsigned short)(verts[i].X / fEncoding.getPosScale());
                pp += 3;
            }
        }
        break;
    case plSpanEncoding::kPos101010:
        {
            unsigned int* pp = (unsigned int*)fPosDelta;
            for (unsigned int i=0; i<fNumVerts; i++) {
                *pp = ((unsigned int)(verts[i].Z / fEncoding.getPosScale()) & 0x3F) << 20
                    | ((unsigned int)(verts[i].Y / fEncoding.getPosScale()) & 0x3F) << 10
                    | ((unsigned int)(verts[i].X / fEncoding.getPosScale()) & 0x3F);
                pp++;
            }
        }
        break;
    case plSpanEncoding::kPos008:
        {
            unsigned char* pp = fPosDelta;
            for (unsigned int i=0; i<fNumVerts; i++) {
                *pp = (unsigned char)(verts[i].Z / fEncoding.getPosScale());
                pp++;
            }
        }
        break;
    }
}
