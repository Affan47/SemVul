callAsFunction(ExecState* exec, JSObject* , const List& args)
{
    double arg = args[0]->toNumber(exec);

    switch (id) {
    case NumberObjectImp::IsFinite:
        if (args[0]->type() != NumberType)
            return jsBoolean(false);
        return jsBoolean(!isNaN(arg) && !isInf(arg));

    case NumberObjectImp::IsInteger:
        {
            if (args[0]->type() != NumberType)
                return jsBoolean(false);
            if (isNaN(arg) || isInf(arg))
                return jsBoolean(false);
            double num = args[0]->toInteger(exec);
            return jsBoolean(num == arg);
        }
    case NumberObjectImp::IsNaN:
        if (args[0]->type() != NumberType)
            return jsBoolean(false);
        return jsBoolean(isNaN(arg));

    case NumberObjectImp::IsSafeInteger:
        {
            if (args[0]->type() != NumberType)
                return jsBoolean(false);
            if (isNaN(arg) || isInf(arg))
                return jsBoolean(false);
            double num = args[0]->toInteger(exec);
            if (num != arg)
                return jsBoolean(false);
            return jsBoolean(abs(num) < MAX_SAFE_INTEGER);
        }
    case NumberObjectImp::ParseInt:
        return jsNumber(KJS::parseInt(args[0]->toString(exec), args[1]->toInt32(exec)));
    case NumberObjectImp::ParseFloat:
        return jsNumber(KJS::parseFloat(args[0]->toString(exec)));

    }
    return jsUndefined();
}
