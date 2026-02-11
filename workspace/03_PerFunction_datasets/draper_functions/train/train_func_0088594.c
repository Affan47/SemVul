InferBasedOnInputs(HValue* current) {
  Representation r = current->representation();
  if (r.IsSpecialization()) return;
  ASSERT(current->CheckFlag(HValue::kFlexibleRepresentation));
  Representation inferred = current->InferredRepresentation();
  if (inferred.IsSpecialization()) {
    current->ChangeRepresentation(inferred);
    AddDependantsToWorklist(current);
  }
}
