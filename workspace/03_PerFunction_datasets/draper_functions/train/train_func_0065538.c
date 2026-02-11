Compare(const Node& rhs) const
	{
		if(m_type != rhs.m_type)
			return rhs.m_type - m_type;

		switch(m_type) {
			case NodeType::Null:
				return 0;
			case NodeType::Scalar:
				return m_scalarData.compare(rhs.m_scalarData);
			case NodeType::Sequence:
				if(m_seqData.size() < rhs.m_seqData.size())
					return 1;
				else if(m_seqData.size() > rhs.m_seqData.size())
					return -1;
				for(std::size_t i=0;i<m_seqData.size();i++)
					if(int cmp = m_seqData[i]->Compare(*rhs.m_seqData[i]))
						return cmp;
				return 0;
			case NodeType::Map:
				if(m_mapData.size() < rhs.m_mapData.size())
					return 1;
				else if(m_mapData.size() > rhs.m_mapData.size())
					return -1;
				node_map::const_iterator it = m_mapData.begin();
				node_map::const_iterator jt = rhs.m_mapData.begin();
				for(;it!=m_mapData.end() && jt!=rhs.m_mapData.end();it++, jt++) {
					if(int cmp = it->first->Compare(*jt->first))
						return cmp;
					if(int cmp = it->second->Compare(*jt->second))
						return cmp;
				}
				return 0;
		}

		assert(false);
		return 0;
	}
