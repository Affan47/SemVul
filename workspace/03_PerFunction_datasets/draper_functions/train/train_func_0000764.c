MapFirst(const OBMol *queried, Mapping &map, const OBBitVec &mask)
      {
        class MapFirstFunctor : public Functor
        {
          private:
            Mapping &m_map;
          public:
            MapFirstFunctor(Mapping &map) : m_map(map)
            {
            }
            bool operator()(Mapping &map)
            {
              m_map = map;

              return true;
            }
        };

        MapFirstFunctor functor(map);
        MapGeneric(functor, queried, mask);
      }
