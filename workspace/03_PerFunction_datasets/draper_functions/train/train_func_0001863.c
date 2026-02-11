unmarshalArguments(cdrStream& _n)
{
  arg_0_ = _n.unmarshalString(0);
  arg_0 = arg_0_.in();
  arg_1_ = _n.unmarshalString(0);
  arg_1 = arg_1_.in();
  arg_2_ = CosPropertyService::PropertySet_Helper::unmarshalObjRef(_n);
  arg_2 = arg_2_.in();
  arg_3_ = CosEventComm::PushConsumer::_unmarshalObjRef(_n);
  arg_3 = arg_3_.in();
  arg_4_ = new CosLicensingManager::Challenge;
  (CosLicensingManager::Challenge&)arg_4_ <<= _n;
  arg_4 = &arg_4_.inout();

}
