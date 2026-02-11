__eq__(const Basic &o) const
{
    if (is_a<FunctionWrapper>(o) &&
        (*comp_)(obj_, static_cast<const FunctionWrapper &>(o).obj_) == 0)
        return true;
    return false;
}
