CQRCreateQuaternion(CQRQuaternionHandle CQR_FAR * quaternion, double w, double x, double y, double z) {

        *quaternion = (CQRQuaternionHandle)CQR_MALLOC(sizeof(CQRQuaternion));

        if (!*quaternion) return CQR_NO_MEMORY;

        (*quaternion)->w = w;
        (*quaternion)->x = x;
        (*quaternion)->y = y;
        (*quaternion)->z = z;

        return CQR_SUCCESS;

    }
