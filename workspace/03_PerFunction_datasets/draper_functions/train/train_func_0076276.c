processRequest(Request& r)
{
    const URL& url = r.getURL();
    bool usePost = r.usePost();
    const std::string* postdata = usePost ? &(r.getPostData()) : 0;

#ifdef GNASH_DEBUG_LOADMOVIE_REQUESTS_PROCESSING
    log_debug("Movie loader thread processing request for target %s",
        r.getTarget());
#endif

	boost::intrusive_ptr<movie_definition> md (
        MovieFactory::makeMovie(url, _movieRoot.runResources(),
                                NULL, true, postdata)
    );
    r.setCompleted(md);

#ifdef GNASH_DEBUG_LOADMOVIE_REQUESTS_PROCESSING
    log_debug("Movie loader thread completed request for target %s",
        r.getTarget());
#endif
}
