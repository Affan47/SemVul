secu_PrintPolicyQualifier(FILE *out,CERTPolicyQualifier *policyQualifier,
			  char *msg,int level)
{
   SECStatus rv;
   SECItem * qualifierValue = &policyQualifier->qualifierValue;

   SECU_PrintObjectID(out, &policyQualifier->qualifierID ,
					"Policy Qualifier Name", level);
   if (!qualifierValue->data) {
	SECU_Indent(out, level);
	fprintf(out,"Error: missing qualifier\n");
   } else
   switch (policyQualifier->oid) {
   case SEC_OID_PKIX_USER_NOTICE_QUALIFIER:
       rv = secu_PrintUserNoticeQualifier(out, qualifierValue, msg, level);
       if (SECSuccess == rv)
	   break;

   case SEC_OID_PKIX_CPS_POINTER_QUALIFIER:
   default:
	SECU_PrintAny(out, qualifierValue, "Policy Qualifier Data", level);
	break;
   }
   return SECSuccess;
}
