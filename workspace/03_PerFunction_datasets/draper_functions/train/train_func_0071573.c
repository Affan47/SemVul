integer_symbol(const char *basename, const Type *t)
{
    if (t->members)
	return "int";
    else if (t->range == NULL)
	return "heim_integer";
    else if (t->range->min < INT_MIN && t->range->max <= INT64_MAX)
	return "int64_t";
    else if (t->range->min >= 0 && t->range->max > UINT_MAX)
	return "uint64_t";
    else if (t->range->min >= INT_MIN && t->range->max <= INT_MAX)
	return "int";
    else if (t->range->min >= 0 && t->range->max <= UINT_MAX)
	return "unsigned";
    else {
	abort();
        UNREACHABLE(return NULL);
    }
}
