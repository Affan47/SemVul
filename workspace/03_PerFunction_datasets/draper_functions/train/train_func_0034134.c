createFilter(Column *column, int operator_id, char *value)
{
    Filter *filter = column->createFilter(operator_id, value);
    if (!filter)
        _output->setError(RESPONSE_CODE_INVALID_HEADER, "cannot create filter on table %s", _table->name());
    else if (filter->hasError()) {
        _output->setError(filter->errorCode(), "error in Filter header: %s", filter->errorMessage().c_str());
        delete filter;
        filter = 0;
    }
    else
        filter->setQuery(this);
    return filter;
}
