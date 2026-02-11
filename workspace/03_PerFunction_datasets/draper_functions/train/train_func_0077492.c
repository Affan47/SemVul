CQRDot (double CQR_FAR * dotprod,  CQRQuaternionHandle q1, CQRQuaternionHandle q2 ) {

        if (!dotprod || !q1 || !q2 ) return CQR_BAD_ARGUMENT;

        *dotprod = q1->w*q2->w + q1->x*q2->x + q1->y*q2->y +q1->z*q2->z;

        return CQR_SUCCESS;

    }
