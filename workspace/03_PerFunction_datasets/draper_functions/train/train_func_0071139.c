ParseExpressionNode_LeftAssociative( MiniTokenizer& mt )
{
    Node* lhs = ParseValueNode( mt ) ;


    while( mt.peek() != ")" )
    {
        std::string op = mt.eat() ;

        if( op.size() == 0 )
        {
            std::cerr << "expression cut short" << std::endl ;
            delete lhs ;
            return new NodeConstantValue( 0. ) ;
        }

        Node* rhs = ParseValueNode( mt ) ;

        lhs = MakeOperationNode( op, lhs, rhs );
    }

    return lhs ;
}
