isPointInside(const Vector3& point) const
    {

        Real anglesum = 0;
        size_t n = getVertexCount();
        for (size_t i = 0; i < n; i++)
        {
            const Vector3& p1 = getVertex(i);
            const Vector3& p2 = getVertex((i + 1) % n);

            Vector3 v1 = p1 - point;
            Vector3 v2 = p2 - point;

            Real len1 = v1.length();
            Real len2 = v2.length();

            if (Math::RealEqual(len1 * len2, 0.0f, 1e-4f))
            {

                return true;
            }
            else
            {
                Real costheta = v1.dotProduct(v2) / (len1 * len2);
                anglesum += acos(costheta);
            }
        }


        return Math::RealEqual(anglesum, Math::TWO_PI, 1e-4f);

    }
