getWorldAABB() const
    {
        Matrix4 m = Matrix4::IDENTITY;
        m.setTrans(getPosition());

        AxisAlignedBox ret = getAABB();
        ret.transformAffine(m);
        return ret;
    }
