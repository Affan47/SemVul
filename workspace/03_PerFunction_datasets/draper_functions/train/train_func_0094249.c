wxString_OpAdd(HSQUIRRELVM v)
    {
        StackHandler sa(v);
        wxString result;
        wxString& str1 = *SqPlus::GetInstance<wxString,false>(v, 1);
        if (sa.GetType(2) == OT_INTEGER)
        {
#ifdef _SQ64
            result.Printf(_T("%s%ld"), str1.c_str(), sa.GetInt(2));
#else
            result.Printf(_T("%s%d"), str1.c_str(), sa.GetInt(2));
#endif
        }
        else if (sa.GetType(2) == OT_FLOAT)
            result.Printf(_T("%s%f"), str1.c_str(), sa.GetFloat(2));
        else if (sa.GetType(2) == OT_USERPOINTER)
            result.Printf(_T("%s%p"), str1.c_str(), sa.GetUserPointer(2));
        else if (sa.GetType(2) == OT_STRING)
            result.Printf(_T("%s%s"), str1.c_str(), cbC2U(sa.GetString(2)).c_str());
        else
            result = str1 + *SqPlus::GetInstance<wxString,false>(v, 2);
        return SqPlus::ReturnCopy(v, result);
    }
