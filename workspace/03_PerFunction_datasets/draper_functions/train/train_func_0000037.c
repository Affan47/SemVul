CrossLinkService(
    ServiceDescriptor* service, const ServiceDescriptorProto& proto) {
  if (service->options_ == NULL) {
    service->options_ = &ServiceOptions::default_instance();
  }

  for (int i = 0; i < service->method_count(); i++) {
    CrossLinkMethod(&service->methods_[i], proto.method(i));
  }
}
