setNamedConstant(const String& name, const Vector2& vec)
    {

        const GpuConstantDefinition* def =
            _findNamedConstantDefinition(name, !mIgnoreMissingParams);
        if (def)
            _writeRawConstant(def->physicalIndex, vec);
    }
