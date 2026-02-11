getContext(UDisplayContextType type) const {
    switch (type) {
        case UDISPCTX_TYPE_DIALECT_HANDLING:
            return (UDisplayContext)dialectHandling;
        case UDISPCTX_TYPE_CAPITALIZATION:
            return capitalizationContext;
        default:
            break;
    }
    return (UDisplayContext)0;
}
