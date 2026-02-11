getObjectClass(const ObjectAddress *object)
{

	if (object->classId != RelationRelationId &&
		object->objectSubId != 0)
		elog(ERROR, "invalid objectSubId 0 for object class %u",
			 object->classId);

	switch (object->classId)
	{
		case RelationRelationId:

			return OCLASS_CLASS;

		case ProcedureRelationId:
			return OCLASS_PROC;

		case TypeRelationId:
			return OCLASS_TYPE;

		case CastRelationId:
			return OCLASS_CAST;

		case CollationRelationId:
			return OCLASS_COLLATION;

		case ConstraintRelationId:
			return OCLASS_CONSTRAINT;

		case ConversionRelationId:
			return OCLASS_CONVERSION;

		case AttrDefaultRelationId:
			return OCLASS_DEFAULT;

		case LanguageRelationId:
			return OCLASS_LANGUAGE;

		case LargeObjectRelationId:
			return OCLASS_LARGEOBJECT;

		case OperatorRelationId:
			return OCLASS_OPERATOR;

		case OperatorClassRelationId:
			return OCLASS_OPCLASS;

		case OperatorFamilyRelationId:
			return OCLASS_OPFAMILY;

		case AccessMethodOperatorRelationId:
			return OCLASS_AMOP;

		case AccessMethodProcedureRelationId:
			return OCLASS_AMPROC;

		case RewriteRelationId:
			return OCLASS_REWRITE;

		case TriggerRelationId:
			return OCLASS_TRIGGER;

		case NamespaceRelationId:
			return OCLASS_SCHEMA;

		case TSParserRelationId:
			return OCLASS_TSPARSER;

		case TSDictionaryRelationId:
			return OCLASS_TSDICT;

		case TSTemplateRelationId:
			return OCLASS_TSTEMPLATE;

		case TSConfigRelationId:
			return OCLASS_TSCONFIG;

		case AuthIdRelationId:
			return OCLASS_ROLE;

		case DatabaseRelationId:
			return OCLASS_DATABASE;

		case TableSpaceRelationId:
			return OCLASS_TBLSPACE;

		case ForeignDataWrapperRelationId:
			return OCLASS_FDW;

		case ForeignServerRelationId:
			return OCLASS_FOREIGN_SERVER;

		case UserMappingRelationId:
			return OCLASS_USER_MAPPING;

		case DefaultAclRelationId:
			return OCLASS_DEFACL;

		case ExtensionRelationId:
			return OCLASS_EXTENSION;
	}


	elog(ERROR, "unrecognized object class: %u", object->classId);
	return OCLASS_CLASS;
}
