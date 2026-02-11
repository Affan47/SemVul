isUnsigned(const Variable* var)
{
    return(var && var->typeStartToken()->isUnsigned() && !var->isPointer() && !var->isArray());
}
