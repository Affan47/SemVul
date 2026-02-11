calculateNormals()
{
    int i,x,y;
    float *buf = NULL;

    for(i=0;i<numVertices;i++) {
        vNormals[i] = Vector3::ZERO;
    }

    buf = vertexBuffers[currentBuffNumber] ;
    unsigned short* vinds = (unsigned short*) indexBuffer->lock(
        0, indexBuffer->getSizeInBytes(), HardwareBuffer::HBL_READ_ONLY);
    float *pNormals = (float*) normVertexBuffer->lock(
        0, normVertexBuffer->getSizeInBytes(), HardwareBuffer::HBL_DISCARD);
    for(i=0;i<numFaces;i++) {
        int p0 = vinds[3*i] ;
        int p1 = vinds[3*i+1] ;
        int p2 = vinds[3*i+2] ;
        Vector3 v0(buf[3*p0], buf[3*p0+1], buf[3*p0+2]);
        Vector3 v1(buf[3*p1], buf[3*p1+1], buf[3*p1+2]);
        Vector3 v2(buf[3*p2], buf[3*p2+1], buf[3*p2+2]);
        Vector3 diff1 = v2 - v1 ;
        Vector3 diff2 = v0 - v1 ;
        Vector3 fn = diff1.crossProduct(diff2);
        vNormals[p0] += fn ;
        vNormals[p1] += fn ;
        vNormals[p2] += fn ;
    }

    for(y=0;y<=complexity;y++) {
        for(x=0;x<=complexity;x++) {
            int numPoint = y*(complexity+1) + x ;
            Vector3 n = vNormals[numPoint] ;
            n.normalise() ;
            float* normal = pNormals + 3*numPoint ;
            normal[0]=n.x;
            normal[1]=n.y;
            normal[2]=n.z;
        }
    }
    indexBuffer->unlock();
    normVertexBuffer->unlock();
}
