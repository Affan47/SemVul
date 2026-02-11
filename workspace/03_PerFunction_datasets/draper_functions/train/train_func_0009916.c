setFrictionConstraintImpulse( btSolverConstraint& solverConstraint,
																		btRigidBody* rb0, btRigidBody* rb1,
																 btManifoldPoint& cp, const btContactSolverInfo& infoGlobal)
{
					if (infoGlobal.m_solverMode & SOLVER_USE_FRICTION_WARMSTARTING)
					{
						{
							btSolverConstraint& frictionConstraint1 = m_tmpSolverContactFrictionConstraintPool[solverConstraint.m_frictionIndex];
							if (infoGlobal.m_solverMode & SOLVER_USE_WARMSTARTING)
							{
								frictionConstraint1.m_appliedImpulse = cp.m_appliedImpulseLateral1 * infoGlobal.m_warmstartingFactor;
								if (rb0)
									rb0->internalApplyImpulse(frictionConstraint1.m_contactNormal*rb0->getInvMass()*rb0->getLinearFactor(),frictionConstraint1.m_angularComponentA,frictionConstraint1.m_appliedImpulse);
								if (rb1)
									rb1->internalApplyImpulse(frictionConstraint1.m_contactNormal*rb1->getInvMass()*rb1->getLinearFactor(),-frictionConstraint1.m_angularComponentB,-frictionConstraint1.m_appliedImpulse);
							} else
							{
								frictionConstraint1.m_appliedImpulse = 0.f;
							}
						}

						if ((infoGlobal.m_solverMode & SOLVER_USE_2_FRICTION_DIRECTIONS))
						{
							btSolverConstraint& frictionConstraint2 = m_tmpSolverContactFrictionConstraintPool[solverConstraint.m_frictionIndex+1];
							if (infoGlobal.m_solverMode & SOLVER_USE_WARMSTARTING)
							{
								frictionConstraint2.m_appliedImpulse = cp.m_appliedImpulseLateral2 * infoGlobal.m_warmstartingFactor;
								if (rb0)
									rb0->internalApplyImpulse(frictionConstraint2.m_contactNormal*rb0->getInvMass(),frictionConstraint2.m_angularComponentA,frictionConstraint2.m_appliedImpulse);
								if (rb1)
									rb1->internalApplyImpulse(frictionConstraint2.m_contactNormal*rb1->getInvMass(),-frictionConstraint2.m_angularComponentB,-frictionConstraint2.m_appliedImpulse);
							} else
							{
								frictionConstraint2.m_appliedImpulse = 0.f;
							}
						}
					} else
					{
						btSolverConstraint& frictionConstraint1 = m_tmpSolverContactFrictionConstraintPool[solverConstraint.m_frictionIndex];
						frictionConstraint1.m_appliedImpulse = 0.f;
						if ((infoGlobal.m_solverMode & SOLVER_USE_2_FRICTION_DIRECTIONS))
						{
							btSolverConstraint& frictionConstraint2 = m_tmpSolverContactFrictionConstraintPool[solverConstraint.m_frictionIndex+1];
							frictionConstraint2.m_appliedImpulse = 0.f;
						}
					}
}
