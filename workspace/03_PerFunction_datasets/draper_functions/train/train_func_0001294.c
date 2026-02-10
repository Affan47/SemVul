parseIf() {
    Node *node ;
    Node *ifpart ;
    if (properties & ALLOW_OMITTED_PARENS) {
        node = single_expression() ;
    } else {
        needbrack (LBRACK) ;
        node = single_expression() ;
        needbrack (RBRACK) ;
    }
    if (node->op == ASSIGN) {
        warning ("Assignment used as condition") ;
    }
    ifpart = parseStatement() ;
    if (match (ELSE)) {
        Node *elsepart = parseStatement() ;
        Node *oldif = ifpart ;
	ifpart = new Node (this,ELSE, ifpart, elsepart) ;
        if (elsepart != NULL) {
	    ifpart->scope = elsepart->scope ;
        } else {
            if (oldif != NULL) {
	        ifpart->scope = oldif->scope ;
            }
        }
    } else if (match (ELIF)) {
	Node *elif = parseIf() ;
	Node *oldif = ifpart ;
	ifpart = new Node (this, ELSE, ifpart, elif) ;
        if (elif != NULL) {
            ifpart->scope = elif->scope ;
        } else {
            if (oldif != NULL) {
	        ifpart->scope = oldif->scope ;
            }
        }
    }

    node = new Node (this,IF, node, ifpart) ;
    if (ifpart != NULL) {
        node->scope = ifpart->scope ;
    }
    return node ;
}
