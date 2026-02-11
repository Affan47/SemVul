AggregateComposer( Collections::AggregateCollection *coll, Meta::ComposerPtr composer )
        : Meta::Composer()
        , Meta::Observer()
        , m_collection( coll )
        , m_name( composer->name() )
{
    m_composers.append( composer );
    subscribeTo( composer );
}
