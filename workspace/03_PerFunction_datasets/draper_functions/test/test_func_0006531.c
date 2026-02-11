typeName(int typeReference)
{
    switch (typeReference) {
    case Depends: return ::TYPE_DEPENDS;
    case Recommends: return ::TYPE_RECOMMENDS;
    case Suggests: return ::TYPE_SUGGESTS;
    case Requires: return ::TYPE_REQUIRES;
    case Conflicts: return ::TYPE_CONFLICTS;
    case Breaks: return ::TYPE_BREAKS;
    case Provides: return ::TYPE_PROVIDES;
    default: return QString::null;
    }
    return QString::null;
}
