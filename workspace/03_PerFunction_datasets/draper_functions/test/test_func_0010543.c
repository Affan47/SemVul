isnsTagText (uint32_t tagid)
{
	switch (tagid)
	{
		case ISNS_DELIMITER          : return("Delimiter");
		case ISNS_ENTITY_ID          : return("Entity Identifier");
		case ISNS_ENTITY_TYPE        : return("Entity Protocol");
		case ISNS_MGMT_IP            : return("Mgmt IP Address");
		case ISNS_TIMESTAMP          : return("Timestamp");
		case ISNS_PROT_VER           : return("Protocol Version Range");
		case ISNS_ENTITY_PERIOD      : return("Entity Period");
		case ISNS_ENTITY_CERT        : return("Entity Certificate");
		case ISNS_PORTAL_IP          : return("Portal IP-Address");
		case ISNS_PORTAL_PORT        : return("Portal TCP/UDP Port");
		case ISNS_PORTAL_SYM_NAME    : return("Portal Symbolic Name");
		case ISNS_ESI_INTERVAL       : return("ESI Interval");
		case ISNS_ESI_PORT           : return("ESI/SCN UDP Port");
		case ISNS_PORTAL_CERT        : return("Portal Certificate");
		case ISNS_ISCSI_NODE_ID      : return("iSCSI Name");
		case ISNS_ISCSI_TYPE         : return("iSCSI Node Type");
		case ISNS_ISCSI_ALIAS        : return("iSCSI Node Alias");
		case ISNS_ISCSI_SCN_BITMAP   : return("iSCSI SCN Bitmap");
		case ISNS_ISCSI_CERT         : return("iSCSI Node Certificate");
		case ISNS_PORT_NAME          : return("Port Name");
		case ISNS_PORT_ID            : return("Port_ID");
		case ISNS_PORT_TYPE          : return("Port_Type");
		case ISNS_PORT_SYM_NAME      : return("Port_Symbolic Name");
		case ISNS_FABRIC_PORT_NAME   : return("FC Fabric Port Name");
		case ISNS_FC_HARD_ADDR       : return("FC Hard Address");
		case ISNS_FC_PORT_IP         : return("FC Port IP-Address");
		case ISNS_FC_COS             : return("FC Class of Service");
		case ISNS_FC4_TYPE           : return("FC FC-4 Types");
		case ISNS_FC4_DESC           : return("FC FC-4 Descriptor");
		case ISNS_FC4_FEATURE        : return("FC FC-4 Features");
		case ISNS_IFCP_SCN_BITMAP    : return("iFCP Node SCN bitmap");
		case ISNS_IFCP_NODE_CERT     : return("iFCP Node Certificate");
		case iSNS_FC4_TYPE_QUERY_KEY : return("FC-4 Type Code");
		case ISNS_NODE_NAME          : return("FC Device WWNN");
		case ISNS_NODE_SYM_NAME      : return("FC Device Sym Node Name");
		case ISNS_FC_NODE_IP         : return("FC Device IP-Address");
		case ISNS_FC_NODE_IPA        : return("FC Device IPA");
		case ISNS_FC_NODE_CERT       : return("FC Device Certificate");
		case ISNS_DDS_ID             : return("Discovery Domain Set ID");
		case ISNS_DDS_SYM_NAME       : return("Discovery Domain Set Symbolic Name");
		case ISNS_DDS_STATUS         : return("Discovery Domain Set Status");
		case ISNS_DD_ID              : return("Discovery Domain ID");
		case ISNS_DD_FEATURE_BITMAP  : return("Discovery Domain Feature Bitmap");
		case ISNS_DD_SYM_NAME        : return("Discovery Domain Symbolic Name");
		case ISNS_DD_ISCSI_MEMBER    : return("Discovery Domain iSCSI Member");
		case ISNS_DD_IFCP_MEMBER     : return("Discovery Domain iFCP Member");
		case ISNS_COMPANY_OUI        : return("Company OUI");
		case ISNS_ENTITY_IDX         : return("Entity Index");
		case ISNS_ISCSI_IDX          : return("iSCSI Index");
		case ISNS_PORTAL_IDX         : return("Portal Index");
		case ISNS_DD_ISCSI_MEMBER_IDX: return("Discovery Domain iSCSI Member Index");
		case ISNS_DD_ACTIVE          : return("Discovery Domain Active");
 		case ISNS_NODE_ACTIVE        : return("Node Active");
		case ISNS_SCN_PORT           : return("SCN Port");
		case ISNS_PORTAL_GROUP       : return("Portal Group Tag (depreciated)");
		case ISNS_PORTAL_GROUP_TAG   : return("Portal Group Tag");
		case ISNS_PORTAL_GROUP_ISCSI_NAME : return("Portal Group ISCSI Name");
		case ISNS_PORTAL_GROUP_IP    : return("Portal Group IP Address");
		case ISNS_PORTAL_GROUP_PORT  : return("Portal Group TCP/UDP Port");
		case ISNS_PORTAL_SECURITY_BITMAP:  return("Portal Security Bitmap");
		default                      : return("Unknown TAG code");
	}
}
