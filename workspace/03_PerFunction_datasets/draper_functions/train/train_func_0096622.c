is_preferable_to(CdlTransaction other) const
{
    CYG_REPORT_FUNCNAMETYPE("CdlTransactionBody::preferable_to", "result %d");
    CYG_REPORT_FUNCARG2XV(this, other);
    CYG_PRECONDITION_THISC();
    CYG_PRECONDITION_CLASSC(other);
    CYG_PRECONDITIONC(this != other);

    bool result = false;
    unsigned int this_changes  = this->changes.size()  + this->activated.size()  + this->deactivated.size();
    unsigned int other_changes = other->changes.size() + other->activated.size() + other->deactivated.size();

    if (this_changes <= other_changes) {
        result = true;
    }

    CYG_REPORT_RETVAL(result);
    return result;
}
