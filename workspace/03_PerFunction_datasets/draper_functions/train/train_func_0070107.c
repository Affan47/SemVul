CreateSrcParser() const
{
   string SourcesURI = _config->FindDir("Dir::State::lists") +
      URItoFileName(IndexURI("Sources"));
   string SourcesURIgzip = SourcesURI + ".gz";

   if (!FileExists(SourcesURI) && !FileExists(SourcesURIgzip))
      return NULL;
   else if (!FileExists(SourcesURI) && FileExists(SourcesURIgzip))
      SourcesURI = SourcesURIgzip;

   return new debSrcRecordParser(SourcesURI,this);
}
