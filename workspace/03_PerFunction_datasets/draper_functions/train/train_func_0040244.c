continueRead()
{


    DEBUG_BLOCK

    while( !atEnd() && error() != CustomError )
    {
        TokenType token = readNext();

        if( error() == PrematureEndOfDocumentError && m_transferJob )
            return true;

        if( hasError() )
        {
            emit doneParsing();
            return false;
        }

        if( m_actionStack.isEmpty() )
        {
            debug() << "expected element on stack!";
            return false;
        }

        const Action* action = m_actionStack.top();
        const Action* subAction = 0;

        switch( token )
        {
            case Invalid:
            {
                debug() << "invalid token received at line " << lineNumber();
                debug() << "Error:\n" << errorString();
                return false;
            }

            case StartDocument:
            case StartElement:
                subAction = action->actionMap()[ elementType() ];

                if( !subAction )
                    subAction = action->actionMap()[ Any ];

                if( !subAction )
                    subAction = &( OpmlParser::sd.skipAction );

                m_actionStack.push( subAction );

                subAction->begin( this );
                break;

            case EndDocument:
            case EndElement:
                action->end( this );

                if( m_actionStack.pop() != action )
                {
                    debug() << "popped other element than expected!";
                }
                break;

            case Characters:
                if( !isWhitespace() || isCDATA() )
                {
                    action->characters( this );
                }


            case Comment:
            case EntityReference:
            case ProcessingInstruction:
            case DTD:
            case NoToken:

                break;
        }
    }

    return !hasError();
}
