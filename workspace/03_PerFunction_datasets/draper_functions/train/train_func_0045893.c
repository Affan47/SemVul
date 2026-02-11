push_tk_link( token_link** chain, token_link* link ) {
    if ( chain && link ) {
        if ( *chain ) {
            link->next = *chain;
        }
        *chain = link;
    }
}
