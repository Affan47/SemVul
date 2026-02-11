checkPresentationState(const DSRCompositeReferenceValue &referenceValue) const
{
    return referenceValue.isEmpty() || (referenceValue.isValid() &&
          (referenceValue.getSOPClassUID() == UID_GrayscaleSoftcopyPresentationStateStorage));
}
