GetHeight( int x, int z )
{
    dReal h=0;
    unsigned char *data_byte;
    short *data_short;
    float *data_float;
    double *data_double;

    if ( m_bWrapMode == 0 )
    {

        if ( x < 0 ) x = 0;
        if ( z < 0 ) z = 0;
        if ( x > m_nWidthSamples - 1 ) x = m_nWidthSamples - 1;
        if ( z > m_nDepthSamples - 1 ) z = m_nDepthSamples - 1;
    }
    else
    {

        x %= m_nWidthSamples - 1;
        z %= m_nDepthSamples - 1;
        if ( x < 0 ) x += m_nWidthSamples - 1;
        if ( z < 0 ) z += m_nDepthSamples - 1;
    }

    switch ( m_nGetHeightMode )
    {


    case 0:
        h = (*m_pGetHeightCallback)(m_pUserData, x, z);
        break;


    case 1:
        data_byte = (unsigned char*)m_pHeightData;
        h = data_byte[x+(z * m_nWidthSamples)];
        break;


    case 2:
        data_short = (short*)m_pHeightData;
        h = data_short[x+(z * m_nWidthSamples)];
        break;


    case 3:
        data_float = (float*)m_pHeightData;
        h = data_float[x+(z * m_nWidthSamples)];
        break;


    case 4:
        data_double = (double*)m_pHeightData;
        h = (dReal)( data_double[x+(z * m_nWidthSamples)] );
        break;
    }

    return (h * m_fScale) + m_fOffset;
}
