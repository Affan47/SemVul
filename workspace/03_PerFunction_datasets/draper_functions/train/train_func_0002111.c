CQRDist (double CQR_FAR * dist, CQRQuaternionHandle q1,  CQRQuaternionHandle q2) {

        if (!q1 || !q2 || !dist ) return CQR_BAD_ARGUMENT;

        CQRMDist(*dist,*q1,*q2);

        return CQR_SUCCESS;

    }
