makeViewMatrix(const Vector3& position, const Quaternion& orientation,
        const Matrix4* reflectMatrix)
    {
        Matrix4 viewMatrix;


        Matrix3 rot;
        orientation.ToRotationMatrix(rot);


        Matrix3 rotT = rot.Transpose();
        Vector3 trans = -rotT * position;


        viewMatrix = Matrix4::IDENTITY;
        viewMatrix = rotT;
        viewMatrix[0][3] = trans.x;
        viewMatrix[1][3] = trans.y;
        viewMatrix[2][3] = trans.z;


        if (reflectMatrix)
        {
            viewMatrix = viewMatrix * (*reflectMatrix);
        }

        return viewMatrix;

    }
