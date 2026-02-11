convertToVariant( KJS::ExecState *exec, KJS::JSValue *value )
{
#ifdef KJSEMBED_VARIANT_DEBUG
    qDebug()<<"KJSEmbed::convertToVariant";
#endif

    QVariant returnValue;
    switch( value->type() )
    {
        case KJS::UndefinedType:
        case KJS::NullType:
            break;
        case KJS::StringType:
            returnValue = toQString(value->toString(exec));
            break;
        case KJS::NumberType:
            returnValue = value->toNumber(exec);
            break;
        case KJS::BooleanType:
            returnValue = value->toBoolean(exec);
            break;
        case KJS::ObjectType:
        {
            KJS::JSObject *obj = value->toObject(exec);

            if ( toQString(obj->className()) == "Array" ) {
                if (checkArray(exec, value) == List)
                    returnValue = convertArrayToList(exec, value);
                else
                    returnValue = convertArrayToMap(exec, value);
            }
            else if ( toQString(obj->className()) == "Date" )
                returnValue = convertDateToDateTime( exec, value );
            else
                returnValue = extractVariant(exec,value);

        } break;
        default:
            returnValue = extractVariant(exec,value);

            break;
    }
    return returnValue;
}
