dumpTree(bool commentsFlag ,Node* pNode  ,unsigned int depth )
{
	if (!pNode) {

		if (nodeStack.size()>1)
			Log::error("nodeStack not emptied: should be 1 but is %d",nodeStack.size());

		for( NodeList::iterator iter = rootNode.children.begin(); iter != rootNode.children.end(); iter++ )
			dumpTree ( commentsFlag,&*iter, depth);
		return;
	}

	std::string indent(depth*2,' ');

	if (commentsFlag) {
		Log::info( "%s%s%s%s%s%s%s%s%s%s",
						indent.c_str(),
						pNode->key.c_str(),
						pNode->value.size()?" = '":"",
						pNode->value.c_str(),
						pNode->value.size()?"'":"",
						( pNode->key.size() + pNode->value.size() > 0 ) ? " ":"",

						pNode->comment.size() && ( pNode->key.size() || pNode->value.size() )?
							((std::string("\n    ")+indent).c_str()) : "",
						pNode->comment.size() && ( pNode->key.size() || pNode->value.size() )   ?"[":"",

						pNode->comment.c_str(),
						pNode->comment.size() && ( pNode->key.size() || pNode->value.size() ) ?"]":""
					);
	} else {

		if ( pNode->key.size() || pNode->value.size())
		{
			Log::info( "%s%s%s%s%s",
					indent.c_str(),
					pNode->key.c_str(),
					pNode->value.size()?" = '":"",
					pNode->value.c_str(),
					pNode->value.size()?"'":""
				);
		}
	}


	for( NodeList::iterator iter = pNode->children.begin(); iter != pNode->children.end(); iter++ )
		dumpTree ( commentsFlag, &*iter, depth+1);
}
