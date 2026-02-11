convertTexAddressMode(TextureUnitState::TextureAddressingMode tam)
    {
        switch (tam)
        {
        case TextureUnitState::TAM_BORDER:
            return "border";
        case TextureUnitState::TAM_CLAMP:
            return "clamp";
        case TextureUnitState::TAM_MIRROR:
            return "mirror";
        case TextureUnitState::TAM_WRAP:
        case TextureUnitState::TAM_UNKNOWN:
            return "wrap";
        }

        return "wrap";
    }
