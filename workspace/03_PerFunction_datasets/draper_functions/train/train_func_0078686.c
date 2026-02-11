CQRSubtract (CQRQuaternionHandle quaternion,  CQRQuaternionHandle q1, CQRQuaternionHandle q2 ) {

        if (!quaternion || !q1 || !q2 ) return CQR_BAD_ARGUMENT;

        CQRMSubtract(*quaternion,*q1,*q2);

        return CQR_SUCCESS;

    }
