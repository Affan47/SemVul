Handle(Arc::Message* msg) const {
  if(blocks_.size()<=0) {
    logger.msg(Arc::ERROR, "LegacyMap: no configurations blocks defined");
    return false;
  };
  Arc::SecAttr* sattr = msg->Auth()->get("ARCLEGACY");
  if(!sattr) {


    Arc::SecAttr* dattr = msg->AuthContext()->get("ARCLEGACYMAP");
    if(dattr) {
      LegacyMapAttr* mattr = dynamic_cast<LegacyMapAttr*>(dattr);
      if(mattr) {

        std::string id = mattr->GetID();
        if(!id.empty()) {
          msg->Attributes()->set("SEC:LOCALID",id);
        };
        return true;
      };
    };
  };
  if(!sattr) sattr = msg->AuthContext()->get("ARCLEGACY");
  if(!sattr) {
    logger.msg(Arc::ERROR, "LegacyPDP: there is no ARCLEGACY Sec Attribute defined. Probably ARC Legacy Sec Handler is not configured or failed.");
    return false;
  };
  LegacySecAttr* lattr = dynamic_cast<LegacySecAttr*>(sattr);
  if(!lattr) {
    logger.msg(Arc::ERROR, "LegacyPDP: ARC Legacy Sec Attribute not recognized.");
    return false;
  };

  AuthUser auth(*msg);
  auth.add_groups(lattr->GetGroups());
  auth.add_vos(lattr->GetVOs());
  std::string id;
  for(std::list<cfgfile>::const_iterator block = blocks_.begin();
                              block!=blocks_.end();++block) {
    LegacyMapCP parser(*block,logger,auth);
    if(!parser) return false;
    if(!parser.Parse()) return false;
    id = parser.LocalID();
    if(!id.empty()) {
      logger.msg(Arc::INFO,"Grid identity is mapped to local identity '%s'",id);
      msg->Attributes()->set("SEC:LOCALID",id);
      break;
    };
  };

  msg->AuthContext()->set("ARCLEGACYMAP",new LegacyMapAttr(id));
  return true;
}
