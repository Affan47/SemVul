takeCommentInRange( int end, int start ) {
    CommentSet::iterator it = m_comments.lower_bound( Comment( 0, end ) );


    while( it != m_comments.begin() && (*it).line() > end ) {
        --it;
    }

    if( it != m_comments.end() && (*it).line() >= start && (*it).line() <= end ) {
        Comment ret = *it;
        m_comments.erase( it );

        return ret;
    } else {
        return Comment();
    }
}
