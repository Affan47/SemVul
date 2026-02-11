makeFlexTag (tokenInfo *const token, flexKind kind)
{
	vString *	fulltag;

	if (FlexKinds [kind].enabled && ! token->ignoreTag )
	{
	DebugStatement (
			debugPrintf (DEBUG_PARSE
				, "\n makeFlexTag start: token isClass:%d  scope:%s  name:%s\n"
				, token->isClass
				, vStringValue(token->scope)
				, vStringValue(token->string)
				);
			);
		if (kind == FLEXTAG_FUNCTION && token->isClass )
		{
			kind = FLEXTAG_METHOD;
		}


		if ( vStringLength(token->scope) > 0 )
		{
			fulltag = vStringNew ();
			vStringCopy(fulltag, token->scope);
			vStringCatS (fulltag, ".");
			vStringCatS (fulltag, vStringValue(token->string));
			vStringTerminate(fulltag);
			vStringCopy(token->string, fulltag);
			vStringDelete (fulltag);
		}
		makeConstTag (token, kind);
	}
}
