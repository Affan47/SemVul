acl_pcpl_match_report(void)
{
    PRECOND(acl_ok);
    char temp[512];
    sprintf(temp, XML_DECL "<D:principal-match xmlns:D='DAV:'>"
		    	"<D:principal-property><D:owner/>"
			"</D:principal-property></D:principal-match>");
    return report_returns_wellformed("Error in REPORT acl-principal-prop-set",temp,"REPORT");
}
