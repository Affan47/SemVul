operator() ( const btBroadphasePair& a1, const btBroadphasePair& b1 )
		{
				btMultiSapBroadphase::btMultiSapProxy* aProxy0 = a1.m_pProxy0 ? (btMultiSapBroadphase::btMultiSapProxy*)a1.m_pProxy0->m_multiSapParentProxy : 0;
				btMultiSapBroadphase::btMultiSapProxy* aProxy1 = a1.m_pProxy1 ? (btMultiSapBroadphase::btMultiSapProxy*)a1.m_pProxy1->m_multiSapParentProxy : 0;
				btMultiSapBroadphase::btMultiSapProxy* bProxy0 = b1.m_pProxy0 ? (btMultiSapBroadphase::btMultiSapProxy*)b1.m_pProxy0->m_multiSapParentProxy : 0;
				btMultiSapBroadphase::btMultiSapProxy* bProxy1 = b1.m_pProxy1 ? (btMultiSapBroadphase::btMultiSapProxy*)b1.m_pProxy1->m_multiSapParentProxy : 0;

				 return aProxy0 > bProxy0 ||
					(aProxy0 == bProxy0 && aProxy1 > bProxy1) ||
					(aProxy0 == bProxy0 && aProxy1 == bProxy1 && a1.m_algorithm > b1.m_algorithm);
		}
}
