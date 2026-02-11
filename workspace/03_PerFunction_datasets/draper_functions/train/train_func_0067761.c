WriteImage(float splatScale) {

    int nPix = xPixelCount * yPixelCount;
    float *rgb = new float[3*nPix];
    int offset = 0;
    for (int y = 0; y < yPixelCount; ++y) {
        for (int x = 0; x < xPixelCount; ++x) {

            XYZToRGB((*pixels)(x, y).Lxyz, &rgb[3*offset]);


            float weightSum = (*pixels)(x, y).weightSum;
            if (weightSum != 0.f) {
                float invWt = 1.f / weightSum;
                rgb[3*offset  ] = max(0.f, rgb[3*offset  ] * invWt);
                rgb[3*offset+1] = max(0.f, rgb[3*offset+1] * invWt);
                rgb[3*offset+2] = max(0.f, rgb[3*offset+2] * invWt);
            }


            float splatRGB[3];
            XYZToRGB((*pixels)(x, y).splatXYZ, splatRGB);
            rgb[3*offset  ] += splatScale * splatRGB[0];
            rgb[3*offset+1] += splatScale * splatRGB[1];
            rgb[3*offset+2] += splatScale * splatRGB[2];
            ++offset;
        }
    }


    ::WriteImage(filename, rgb, NULL, xPixelCount, yPixelCount,
                 xResolution, yResolution, xPixelStart, yPixelStart);


    delete[] rgb;
}
