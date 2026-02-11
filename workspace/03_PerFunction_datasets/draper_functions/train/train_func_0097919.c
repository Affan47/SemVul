_writeRawConstant(size_t physicalIndex, const Matrix4& m, size_t elementCount)
    {


        if (mTransposeMatrices)
        {
            Matrix4 t = m.transpose();
            _writeRawConstants(physicalIndex, t[0], elementCount > 16 ? 16 : elementCount);
        }
        else
        {
            _writeRawConstants(physicalIndex, m[0], elementCount > 16 ? 16 : elementCount);
        }

    }
