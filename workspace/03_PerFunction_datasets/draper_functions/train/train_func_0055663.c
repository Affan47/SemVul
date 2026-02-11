makeCopy() const
	    {
			return new GR_CairoPangoItem(pango_item_copy(m_pi));
		}
