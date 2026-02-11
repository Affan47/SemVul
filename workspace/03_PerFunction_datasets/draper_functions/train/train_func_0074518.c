int_val() {
    switch (type()) {
    case AttributeValue::CharType:
	return (int) char_val();
    case AttributeValue::UCharType:
	return (int) uchar_val();
    case AttributeValue::ShortType:
	return (int) short_val();
    case AttributeValue::UShortType:
	return (int) ushort_val();
    case AttributeValue::IntType:
	return int_ref();
    case AttributeValue::UIntType:
	return (int) uint_val();
    case AttributeValue::LongType:
	return (int) long_val();
    case AttributeValue::ULongType:
	return (int) ulong_val();
    case AttributeValue::FloatType:
	return (int) float_val();
    case AttributeValue::DoubleType:
	return (int) double_val();
    case AttributeValue::BooleanType:
	return (int) boolean_val();
    case AttributeValue::SymbolType:
	return int_ref();
    case AttributeValue::ObjectType:
        return (int) (long) obj_val();
    default:
	return 0;
    }
}
