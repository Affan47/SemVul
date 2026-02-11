addMatch( const Meta::GenrePtr &genre )
{
    if ( d->closestParent > Private::GENRE )
    {
        d->closestParent = Private::GENRE;
        const Meta::ScriptableServiceGenre * scriptableGenre = static_cast< const Meta::ScriptableServiceGenre * >( genre.data() );
        d->callbackString = scriptableGenre->callbackString();
        d->parentId = scriptableGenre->id();
    }
    return this;
}
