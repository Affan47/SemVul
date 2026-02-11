IsInverse(const FCDTransform* transform) const
{
	return transform->GetType() == FCDTransform::TRANSLATION
		&& IsEquivalent(-1.0f * translation, ((const FCDTTranslation*)transform)->translation);
}
