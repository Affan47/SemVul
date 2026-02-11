parseMatrix3(const String& val, const Matrix3& defaultValue)
    {

        vector<String>::type vec = StringUtil::split(val);

        if (vec.size() != 9)
        {
            return defaultValue;
        }
        else
        {
            return Matrix3(parseReal(vec[0], defaultValue[0][0]),
                           parseReal(vec[1], defaultValue[0][1]),
                           parseReal(vec[2], defaultValue[0][2]),

                           parseReal(vec[3], defaultValue[1][0]),
                           parseReal(vec[4], defaultValue[1][1]),
                           parseReal(vec[5], defaultValue[1][2]),

                           parseReal(vec[6], defaultValue[2][0]),
                           parseReal(vec[7], defaultValue[2][1]),
                           parseReal(vec[8], defaultValue[2][2]));
        }
    }
