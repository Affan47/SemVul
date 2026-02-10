apply(CEGUI::PropertySet& target) const
    {
        CEGUI_TRY
        {
            target.setProperty(d_propertyName, d_propertyValue);
        }

        CEGUI_CATCH (UnknownObjectException&)
        {}
    }
