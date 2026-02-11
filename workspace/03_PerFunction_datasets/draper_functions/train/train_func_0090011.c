driIndexConfigAttrib(const __DRIconfig *config, int index,
		     unsigned int *attrib, unsigned int *value)
{
    if (index >= 0 && index < ARRAY_SIZE(attribMap)) {
	*attrib = attribMap[index].attrib;
	return driGetConfigAttribIndex(config, index, value);
    }

    return GL_FALSE;
}
