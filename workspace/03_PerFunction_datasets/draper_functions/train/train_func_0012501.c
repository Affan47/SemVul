addOtherFields (tagEntryInfo* const tag, const tagType type,
							const statementInfo *const st,
							vString *const scope, vString *const typeRef)
{


	switch (type)
	{
		default: break;

		case TAG_FUNCTION:
		case TAG_METHOD:
		case TAG_PROTOTYPE:
			if (vStringLength (Signature) > 0)
				tag->extensionFields.signature = vStringValue (Signature);
		case TAG_CLASS:
		case TAG_ENUM:
		case TAG_ENUMERATOR:
		case TAG_EVENT:
		case TAG_FIELD:
		case TAG_INTERFACE:
		case TAG_MEMBER:
		case TAG_NAMESPACE:
		case TAG_PROPERTY:
		case TAG_STRUCT:
		case TAG_TASK:
		case TAG_TYPEDEF:
		case TAG_UNION:
			if (vStringLength (scope) > 0  &&
				(isMember (st) || st->parent->declaration == DECL_NAMESPACE))
			{
				if (isType (st->context, TOKEN_NAME))
					tag->extensionFields.scope [0] = tagName (TAG_CLASS);
				else
					tag->extensionFields.scope [0] =
						tagName (declToTagType (parentDecl (st)));
				tag->extensionFields.scope [1] = vStringValue (scope);
			}
			if ((type == TAG_CLASS  ||  type == TAG_INTERFACE  ||
				 type == TAG_STRUCT) && vStringLength (st->parentClasses) > 0)
			{

				tag->extensionFields.inheritance =
						vStringValue (st->parentClasses);
			}
			if (st->implementation != IMP_DEFAULT &&
				(isLanguage (Lang_cpp) || isLanguage (Lang_csharp) ||
				 isLanguage (Lang_java)))
			{
				tag->extensionFields.implementation =
						implementationString (st->implementation);
			}
			if (isMember (st))
			{
				tag->extensionFields.access = accessField (st);
			}
			break;
	}


	if ((type == TAG_TYPEDEF || type == TAG_VARIABLE || type == TAG_MEMBER)
			&& isContextualStatement(st))
	{
		char *p;

		tag->extensionFields.typeRef [0] =
						tagName (declToTagType (st->declaration));
		p = vStringValue (st->blockName->name);


		if (p == NULL || *p == '\0')
		{
			tokenInfo *const prev2 = prevToken (st, 2);
			if (isType (prev2, TOKEN_NAME))
				p = vStringValue (prev2->name);
		}


		if (vStringLength (scope) > 0)
		{
			vStringCopy(typeRef, scope);
			addContextSeparator (typeRef);
			vStringCatS(typeRef, p);
			p = vStringValue (typeRef);
		}
		tag->extensionFields.typeRef [1] = p;
	}
}
