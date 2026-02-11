printatt(unsigned attributeId,
		 Form_pg_attribute attributeP,
		 char *value)
{
	printf("\t%2d: %s%s%s%s\t(typeid = %u, len = %d, typmod = %d, byval = %c)\n",
		   attributeId,
		   NameStr(attributeP->attname),
		   value != NULL ? " = \"" : "",
		   value != NULL ? value : "",
		   value != NULL ? "\"" : "",
		   (unsigned int) (attributeP->atttypid),
		   attributeP->attlen,
		   attributeP->atttypmod,
		   attributeP->attbyval ? 't' : 'f');
}
