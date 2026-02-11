particleFitsInBBox(const SimpleParticle &particle) const
    {
      return
        (
          (
            m_periodicDimensions[0]
            ||
            (
              m_bBox.contains(particle.getPos() - Vec3(particle.getRad(), 0, 0), getTolerance())
              &&
              m_bBox.contains(particle.getPos() + Vec3(particle.getRad(), 0, 0), getTolerance())
            )
          )
          &&
          (
            m_periodicDimensions[1]
            ||
            (
              m_bBox.contains(particle.getPos() - Vec3(0, particle.getRad(), 0), getTolerance())
              &&
              m_bBox.contains(particle.getPos() + Vec3(0, particle.getRad(), 0), getTolerance())
            )
          )
          &&
          (
            is2d() || m_periodicDimensions[2]
            ||
            (
              m_bBox.contains(particle.getPos() - Vec3(0, 0, particle.getRad()), getTolerance())
              &&
              m_bBox.contains(particle.getPos() + Vec3(0, 0, particle.getRad()), getTolerance())
            )
          )
        );
    }
