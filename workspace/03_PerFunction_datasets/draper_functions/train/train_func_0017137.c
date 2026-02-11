createItem( ItemType type ) const
{
#if 0
    switch( type ) {
    case TypeEvent:   return 0;
    case TypeTask:    return new TaskItem;
    case TypeSummary: return new SummaryItem;
    default:          return 0;
    }
#endif

    Q_UNUSED( type );
    return new GraphicsItem;
}
