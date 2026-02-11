ValidateServiceOptions(ServiceDescriptor* service,
    const ServiceDescriptorProto& proto) {
  if (IsLite(service->file())) {
    AddError(service->full_name(), proto,
             DescriptorPool::ErrorCollector::NAME,
             "Files with optimize_for = LITE_RUNTIME cannot define services.");
  }

  VALIDATE_OPTIONS_FROM_ARRAY(service, method, Method);
}
