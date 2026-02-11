returnFunction( Collections::QueryMaker::ReturnFunction function, qint64 value )
{
    switch( function )
    {
        case Collections::QueryMaker::Count:
        {
            switch( value )
            {
                case Meta::valUrl:
                case Meta::valTitle:
                {
                    return new TrackCounter();
                }
                case Meta::valArtist:
                {
                    return new ArtistCounter();
                }
                case Meta::valAlbum:
                {
                    return new AlbumCounter();
                }
                case Meta::valGenre:
                {
                    return new GenreCounter();
                }
                case Meta::valComposer:
                {
                    return new ComposerCounter();
                }
                case Meta::valYear:
                {
                    return new YearCounter();
                }
                default:
                    return 0;
            }
        }
        case Collections::QueryMaker::Sum:
        {
            CustomReturnValue *crv = CustomValueFactory::returnValue( value );
            return crv ? new SumReturnFunction( crv ) : 0;
        }
        case Collections::QueryMaker::Min:
        {
            CustomReturnValue *crv = CustomValueFactory::returnValue( value );
            return crv ? new MinimumReturnFunction( crv ) : 0;
        }
        case Collections::QueryMaker::Max:
        {
            CustomReturnValue *crv = CustomValueFactory::returnValue( value );
            return crv ? new MaximumReturnFunction( crv ) : 0;
        }
        default:
            return 0;
    }
}
