_invert33(float *a, float *b, float *c, float *dst)
{
    float m00, m01, m02;
    float m10, m11, m12;
    float m20, m21, m22;
    float c00, c01, c02;
    float c10, c11, c12;
    float c20, c21, c22;
    float det;

    m00 = *a++;
    m01 = *a++;
    m02 = *a++;
    m10 = *b++;
    m11 = *b++;
    m12 = *b++;
    m20 = *c++;
    m21 = *c++;
    m22 = *c++;

    c00 = m11*m22 - m12*m21;
    c01 = m10*m22 - m20*m12;
    c02 = m10*m21 - m20*m11;
    c10 = m01*m22 - m21*m02;
    c11 = m00*m22 - m02*m20;
    c12 = m00*m21 - m20*m01;
    c20 = m01*m12 - m11*m02;
    c21 = m00*m12 - m10*m02;
    c22 = m00*m11 - m10*m01;

    det = m00*c00 - m10*c10 + m20*c20;

    if (det == 0.0)
	return 0;

    det = 1.0 / det;

    *dst++ =  det * c00;
    *dst++ = -det * c10;
    *dst++ =  det * c20;
    *dst++ = -det * c01;
    *dst++ =  det * c11;
    *dst++ = -det * c21;
    *dst++ =  det * c02;
    *dst++ = -det * c12;
    *dst++ =  det * c22;

    return 1;
}
