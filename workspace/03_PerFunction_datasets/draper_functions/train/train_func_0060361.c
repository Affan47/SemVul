convert(const Value& value, UnitPtr toUnit) const
{
    if (!toUnit.isNull() && !value.unit().isNull() && value.unit()->isValid()) {
        UnitCategory* category = value.unit()->category();
        if (category) {
            return category->convert(value, toUnit);
        }
    }
    return Value();
}
